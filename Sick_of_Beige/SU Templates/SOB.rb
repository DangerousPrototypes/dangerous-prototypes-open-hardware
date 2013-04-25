# Sick of Beige Google Sketchup plugin
# This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.
# Copyright Taylan Ayken 2012
# http://dangerousprototypes.com
 
require 'sketchup.rb'

module SOB

# User defined values for our design
# All values are actually mm but we are using m for Eagle compatibility
@pcbWidth = 60.m
@pcbLength = 37.m
@areaHeight = 14.6.m							# Height of the inside volume of box, calculate by standoff lengths + PCB thickness
@acrylicThickness = 3.m							# Thickness of acrylic piece we are using
@sideType = 2									# 0: no side piece, 1: interlocking style, 2: stacked style

# Some other values, you shouldn't have to edit these, we will add some advanced options in the future
@holeDiameter = 3.m								# Mounting hole diameter
@holeToEdgeDistance = 4.m						# Distance between mounting hole center and PCB edge
@pcbToSideDistance = 1.m						# Distance between PCB and side piece
@slotLength = 10.m								# Length of our slot
@slotToEdgeDistance = 2*@acrylicThickness		# For making the case strong enough
@cornerRadius = 4.m								# Corner radius for top & bottom pieces
@color = 0xccebf4								# Acrylic color
@alpha = 0.5									# Make it transparent

# Global variables used for creating slots
@longSlot = []
@shortSlot = []

# Used for creating the top & bottom piece.
def SOB.create_top_bottom(x,y,z)
	# Save operation for ease of Undo
	model = Sketchup.active_model
	
	# Create as a group
    entities = model.active_entities
    group = entities.add_group
    entities = group.entities
	
	# Create the rough shape of the bottom piece
	centerPt = Geom::Point3d.new(x,y,z)		# For creating other points
	
	# 4 corners of our piece
	if @sideType == 0
		northWestPt = centerPt + [-@pcbWidth/2,@pcbLength/2,0] + [-@pcbToSideDistance,@pcbToSideDistance,0]
		northEastPt = centerPt + [@pcbWidth/2,@pcbLength/2,0] + [@pcbToSideDistance,@pcbToSideDistance,0]
		southWestPt = centerPt + [-@pcbWidth/2,-@pcbLength/2,0] + [-@pcbToSideDistance,-@pcbToSideDistance,0]
		southEastPt = centerPt + [@pcbWidth/2,-@pcbLength/2,0] + [@pcbToSideDistance,-@pcbToSideDistance,0]
	else
		northWestPt = centerPt + [-@pcbWidth/2,@pcbLength/2,0] + [-@pcbToSideDistance,@pcbToSideDistance,0] + [-@acrylicThickness,@acrylicThickness,0] + [-@slotToEdgeDistance,@slotToEdgeDistance,0]
		northEastPt = centerPt + [@pcbWidth/2,@pcbLength/2,0] + [@pcbToSideDistance,@pcbToSideDistance,0] + [@acrylicThickness,@acrylicThickness,0] + [@slotToEdgeDistance,@slotToEdgeDistance,0]
		southWestPt = centerPt + [-@pcbWidth/2,-@pcbLength/2,0] + [-@pcbToSideDistance,-@pcbToSideDistance,0] + [-@acrylicThickness,-@acrylicThickness,0] + [-@slotToEdgeDistance,-@slotToEdgeDistance,0]
		southEastPt = centerPt + [@pcbWidth/2,-@pcbLength/2,0] + [@pcbToSideDistance,-@pcbToSideDistance,0] + [@acrylicThickness,-@acrylicThickness,0] + [@slotToEdgeDistance,-@slotToEdgeDistance,0]
	end
	
	# Create sides for the part
	north = entities.add_line northWestPt + [@cornerRadius,0,0], northEastPt + [-@cornerRadius,0,0]
	east = entities.add_line northEastPt + [0,-@cornerRadius,0], southEastPt + [0,@cornerRadius,0]
	south = entities.add_line southEastPt + [-@cornerRadius,0,0], southWestPt + [@cornerRadius,0,0]
	west = entities.add_line southWestPt + [0,@cornerRadius,0], northWestPt + [0,-@cornerRadius,0]
	
	# Create rounded corners for this part
	nwCorner = entities.add_arc northWestPt + [@cornerRadius,-@cornerRadius,0], [0,1,0],[0,0,1], @cornerRadius, 0, 90.degrees
	neCorner = entities.add_arc northEastPt + [-@cornerRadius,-@cornerRadius,0], [1,0,0],[0,0,1], @cornerRadius, 0, 90.degrees
	swCorner = entities.add_arc southWestPt + [@cornerRadius,@cornerRadius,0], [-1,0,0],[0,0,1], @cornerRadius, 0, 90.degrees
	seCorner = entities.add_arc southEastPt + [-@cornerRadius,@cornerRadius,0], [0,-1,0],[0,0,1], @cornerRadius, 0, 90.degrees

	# Add all of them to an array in correct order to create the face
	sides = []
	sides << north
	sides.concat(neCorner)
	sides << east
	sides.concat(seCorner)
	sides << south
	sides.concat(swCorner)
	sides << west
	sides.concat(nwCorner)	
	bottom = entities.add_face sides
	
	# Pushpull for adding the 3rd dimention
    bottom.pushpull -@acrylicThickness
	
	# Create the mounting holes
	# We couldn't create a new face on an existing face, +1.m is for that, kind of a cheat :)
	holes = []
	holes[0] = centerPt + [-@pcbWidth/2,@pcbLength/2,0] + [@holeToEdgeDistance,-@holeToEdgeDistance,@acrylicThickness]
	holes[1] = centerPt + [@pcbWidth/2,@pcbLength/2,0] + [-@holeToEdgeDistance,-@holeToEdgeDistance,@acrylicThickness]
	holes[2] = centerPt + [-@pcbWidth/2,-@pcbLength/2,0] + [@holeToEdgeDistance,@holeToEdgeDistance,@acrylicThickness]
	holes[3] = centerPt + [@pcbWidth/2,-@pcbLength/2,0] + [-@holeToEdgeDistance,@holeToEdgeDistance,@acrylicThickness]
	
	holes.each do |i|
		circle = entities.add_circle i, [0,0,1], @holeDiameter/2
		circle[0].faces[0].pushpull -@acrylicThickness
	end
	
	# Create slots if sidepanels will be added
	if @sideType > 0
		# Calculate parameters for width of the board
		numSectionsW = Integer(@pcbWidth/@slotLength)
		numTabsW = [Integer(numSectionsW/2), numSectionsW-Integer(numSectionsW/2)].max
		emptySpaceW = @pcbWidth - (2*numTabsW-1)*@slotLength

		# Calculate parameters for length of the board	
		numSectionsL = Integer(@pcbLength/@slotLength)
		numTabsL = [Integer(numSectionsL/2), numSectionsL-Integer(numSectionsL/2)].max
		emptySpaceL = @pcbLength - (2*numTabsL-1)*@slotLength
		
		# Create initial guide points at the corners
		nSlots = []
		sSlots = []
		wSlots = []
		eSlots = []
		nSlots[0] = centerPt + [-@pcbWidth/2,@pcbLength/2,0] + [0,@pcbToSideDistance,@acrylicThickness] + [emptySpaceW/2,0,0]
		sSlots[0] = centerPt + [@pcbWidth/2,-@pcbLength/2,0] + [0,-@pcbToSideDistance,@acrylicThickness] + [-emptySpaceW/2,0,0]
		wSlots[0] = centerPt + [-@pcbWidth/2,-@pcbLength/2,0] + [-@pcbToSideDistance,0,@acrylicThickness] + [0,emptySpaceL/2,0]
		eSlots[0] = centerPt + [@pcbWidth/2,@pcbLength/2,0] + [@pcbToSideDistance,0,@acrylicThickness] + [0,-emptySpaceL/2,0]

		# Fill in the arrays
		for i in 1...numTabsW
			nSlots[i] = nSlots[0] + [(2*i*@slotLength),0,0]
			sSlots[i] = sSlots[0] + [(-2*i*@slotLength),0,0]
		end
		
		for i in 1...numTabsL
			wSlots[i] = wSlots[0] + [0,(2*i*@slotLength),0]
			eSlots[i] = eSlots[0] + [0,(-2*i*@slotLength),0]
		end

		for i in 0...numTabsW
			ptsN = []
			ptsN[0] = nSlots[i]
			ptsN[1] = nSlots[i] + [@slotLength,0,0]
			ptsN[2] = nSlots[i] + [@slotLength,@acrylicThickness,0]
			ptsN[3] = nSlots[i] + [0,@acrylicThickness,0]
			slotN = entities.add_face ptsN
			slotN.pushpull -@acrylicThickness

			ptsS = []
			ptsS[0] = sSlots[i]
			ptsS[1] = sSlots[i] + [-@slotLength,0,0]
			ptsS[2] = sSlots[i] + [-@slotLength,-@acrylicThickness,0]
			ptsS[3] = sSlots[i] + [0,-@acrylicThickness,0]
			slotS = entities.add_face ptsS
			slotS.pushpull -@acrylicThickness
		end
		
		for i in 0...numTabsL
			ptsW = []
			ptsW[0] = wSlots[i]
			ptsW[1] = wSlots[i] + [0,@slotLength,0]
			ptsW[2] = wSlots[i] + [-@acrylicThickness,@slotLength,0]
			ptsW[3] = wSlots[i] + [-@acrylicThickness,0,0]
			slotW = entities.add_face ptsW
			slotW.pushpull -@acrylicThickness

			ptsE = []
			ptsE[0] = eSlots[i]
			ptsE[1] = eSlots[i] + [0,-@slotLength,0]
			ptsE[2] = eSlots[i] + [@acrylicThickness,-@slotLength,0]
			ptsE[3] = eSlots[i] + [@acrylicThickness,0,0]
			slotE = entities.add_face ptsE
			slotE.pushpull -@acrylicThickness
		end
		
		# Export slots for side piece creation
		@longSlot = nSlots
		@shortSlot = wSlots
	end
	
	# Turn side material into acrylic
	group.material = @color
	group.material.alpha = @alpha
	
    # End the operation
    model.commit_operation
end

def SOB.create_width_side1
	# Save operation for ease of Undo
	model = Sketchup.active_model
	
	# Create as a group
    entities = model.active_entities
    group = entities.add_group
    entities = group.entities
	
	# Create the side panel
	panel = []
	panel[0] = Geom::Point3d.new(0,0,0) + [-@pcbWidth/2,@pcbLength/2,0] + [-@pcbToSideDistance,@pcbToSideDistance,@acrylicThickness] + [-@acrylicThickness,0,0]
	panel[1] = Geom::Point3d.new(0,0,0) + [@pcbWidth/2,@pcbLength/2,0] + [@pcbToSideDistance,@pcbToSideDistance,@acrylicThickness]
	panel[2] = panel[1] + [0,0,@areaHeight/4]
	panel[3] = panel[2] + [@acrylicThickness,0,0]
	panel[4] = panel[3] + [0,0,@areaHeight/2]
	panel[5] = panel[2] + [0,0,@areaHeight/2]
	panel[6] = panel[1] + [0,0,@areaHeight]
	panel[7] = panel[0] + [0,0,@areaHeight]
	panel[8] = panel[7] + [0,0,-@areaHeight/4]
	panel[9] = panel[8] + [@acrylicThickness,0,0]
	panel[10] = panel[9] + [0,0,-@areaHeight/2]
	panel[11] = panel[0] + [0,0,@areaHeight/4]
	side = entities.add_face panel
	side.pushpull -@acrylicThickness
	
	# Fill the lower slots with tabs
	for i in 0...@longSlot.length
		pts = []
		pts[0] = @longSlot[i]
		pts[1] = @longSlot[i] + [@slotLength,0,0]
		pts[2] = @longSlot[i] + [@slotLength,@acrylicThickness,0]
		pts[3] = @longSlot[i] + [0,@acrylicThickness,0]
		tab = entities.add_face pts
		tab.pushpull @acrylicThickness
	end
	
	# Fill the upper slots with tabs
	for i in 0...@longSlot.length
		pts = []
		pts[0] = @longSlot[i] + [0,0,@areaHeight]
		pts[1] = @longSlot[i] + [0,0,@areaHeight] + [@slotLength,0,0]
		pts[2] = @longSlot[i] + [0,0,@areaHeight] + [@slotLength,@acrylicThickness,0]
		pts[3] = @longSlot[i] + [0,0,@areaHeight] + [0,@acrylicThickness,0]
		tab = entities.add_face pts
		tab.pushpull @acrylicThickness
	end
	
	# Turn side material into acrylic
	group.material = @color
	group.material.alpha = @alpha
	
	# Create the other side
	side2 = group.copy
	t = Geom::Transformation.new([0,0,0], [0,0,1], 180.degrees)
	side2 = side2.move!(t)
	
	# Turn side2 material into acrylic
	side2.material = @color
	side2.material.alpha = @alpha
	
    # End the operation
    model.commit_operation
end

def SOB.create_length_side1
	# Save operation for ease of Undo
	model = Sketchup.active_model
	
	# Create as a group
    entities = model.active_entities
    group = entities.add_group
    entities = group.entities
	
	# Create the side panel
	panel = []
	panel[0] = Geom::Point3d.new(0,0,0) + [-@pcbWidth/2,-@pcbLength/2,0] + [-@pcbToSideDistance,-@pcbToSideDistance,@acrylicThickness] + [0,-@acrylicThickness,0]
	panel[1] = Geom::Point3d.new(0,0,0) + [-@pcbWidth/2,@pcbLength/2,0] + [-@pcbToSideDistance,@pcbToSideDistance,@acrylicThickness]
	panel[2] = panel[1] + [0,0,@areaHeight/4]
	panel[3] = panel[2] + [0,@acrylicThickness,0]
	panel[4] = panel[3] + [0,0,@areaHeight/2]
	panel[5] = panel[2] + [0,0,@areaHeight/2]
	panel[6] = panel[1] + [0,0,@areaHeight]
	panel[7] = panel[0] + [0,0,@areaHeight]
	panel[8] = panel[7] + [0,0,-@areaHeight/4]
	panel[9] = panel[8] + [0,@acrylicThickness,0]
	panel[10] = panel[9] + [0,0,-@areaHeight/2]
	panel[11] = panel[0] + [0,0,@areaHeight/4]
	side = entities.add_face panel
	side.pushpull -@acrylicThickness
	
	# Fill the lower slots with tabs
	for i in 0...@shortSlot.length
		pts = []
		pts[0] = @shortSlot[i]
		pts[1] = @shortSlot[i] + [0,@slotLength,0]
		pts[2] = @shortSlot[i] + [-@acrylicThickness,@slotLength,0]
		pts[3] = @shortSlot[i] + [-@acrylicThickness,0,0]
		tab = entities.add_face pts
		tab.pushpull @acrylicThickness
	end
	
	# Fill the upper slots with tabs
	for i in 0...@shortSlot.length
		pts = []
		pts[0] = @shortSlot[i] + [0,0,@areaHeight]
		pts[1] = @shortSlot[i] + [0,0,@areaHeight] + [0,@slotLength,0]
		pts[2] = @shortSlot[i] + [0,0,@areaHeight] + [-@acrylicThickness,@slotLength,0]
		pts[3] = @shortSlot[i] + [0,0,@areaHeight] + [-@acrylicThickness,0,0]
		tab = entities.add_face pts
		tab.pushpull @acrylicThickness
	end
	
	# Turn side material into acrylic
	group.material = @color
	group.material.alpha = @alpha
	
	# Create the other sides
	side2 = group.copy
	t = Geom::Transformation.new([0,0,0], [0,0,1], 180.degrees)
	side2 = side2.move!(t)
	
	# Turn side2 material into acrylic
	side2.material = @color
	side2.material.alpha = @alpha
	
    # End the operation
    model.commit_operation
end

def SOB.create_width_side2
	# Save operation for ease of Undo
	model = Sketchup.active_model
	
	# Create as a group
    entities = model.active_entities
    group = entities.add_group
    entities = group.entities
	
	# Create the side panel
	panel = []
	panel[0] = Geom::Point3d.new(0,0,0) + [-@pcbWidth/2,@pcbLength/2,0] + [-@pcbToSideDistance,@pcbToSideDistance,@acrylicThickness] + [-@acrylicThickness,0,0]
	panel[1] = Geom::Point3d.new(0,0,0) + [@pcbWidth/2,@pcbLength/2,0] + [@pcbToSideDistance,@pcbToSideDistance,@acrylicThickness] + [@acrylicThickness,0,0]
	panel[2] = panel[1] + [0,0,@areaHeight/2]
	panel[3] = panel[2] + [-@acrylicThickness,0,0]
	panel[4] = panel[3] + [0,0,@areaHeight/2]
	panel[5] = panel[0] + [@acrylicThickness,0,@areaHeight] 
	panel[6] = panel[0] + [@acrylicThickness,0,@areaHeight/2]
	panel[7] = panel[0] + [0,0,@areaHeight/2]
	side = entities.add_face panel
	side.pushpull -@acrylicThickness
	
	# Fill the lower slots with tabs
	for i in 0...@longSlot.length
		pts = []
		pts[0] = @longSlot[i]
		pts[1] = @longSlot[i] + [@slotLength,0,0]
		pts[2] = @longSlot[i] + [@slotLength,@acrylicThickness,0]
		pts[3] = @longSlot[i] + [0,@acrylicThickness,0]
		tab = entities.add_face pts
		tab.pushpull @acrylicThickness
	end
	
	# Fill the upper slots with tabs
	for i in 0...@longSlot.length
		pts = []
		pts[0] = @longSlot[i] + [0,0,@areaHeight]
		pts[1] = @longSlot[i] + [0,0,@areaHeight] + [@slotLength,0,0]
		pts[2] = @longSlot[i] + [0,0,@areaHeight] + [@slotLength,@acrylicThickness,0]
		pts[3] = @longSlot[i] + [0,0,@areaHeight] + [0,@acrylicThickness,0]
		tab = entities.add_face pts
		tab.pushpull @acrylicThickness
	end
	
	# Turn side material into acrylic
	group.material = @color
	group.material.alpha = @alpha
	
	# Create the other side
	side2 = group.copy
	t = Geom::Transformation.new([0,0,0], [0,0,1], 180.degrees)
	side2 = side2.move!(t)
	
	# Turn side2 material into acrylic
	side2.material = @color
	side2.material.alpha = @alpha
	
    # End the operation
    model.commit_operation
end

def SOB.create_length_side2
	# Save operation for ease of Undo
	model = Sketchup.active_model
	
	# Create as a group
    entities = model.active_entities
    group = entities.add_group
    entities = group.entities
	
	# Create the side panel
	panel = []
	panel[0] = Geom::Point3d.new(0,0,0) + [-@pcbWidth/2,-@pcbLength/2,0] + [-@pcbToSideDistance,-@pcbToSideDistance,@acrylicThickness]
	panel[1] = Geom::Point3d.new(0,0,0) + [-@pcbWidth/2,@pcbLength/2,0] + [-@pcbToSideDistance,@pcbToSideDistance,@acrylicThickness]
	panel[2] = panel[1] + [0,0,@areaHeight/2]
	panel[3] = panel[2] + [0,@acrylicThickness,0]
	panel[4] = panel[3] + [0,0,@areaHeight/2]
	panel[5] = panel[0] + [0,-@acrylicThickness,@areaHeight] 
	panel[6] = panel[0] + [0,-@acrylicThickness,@areaHeight/2] 
	panel[7] = panel[0] + [0,0,@areaHeight/2]
	side = entities.add_face panel
	side.pushpull -@acrylicThickness
	
	# Fill the lower slots with tabs
	for i in 0...@shortSlot.length
		pts = []
		pts[0] = @shortSlot[i]
		pts[1] = @shortSlot[i] + [0,@slotLength,0]
		pts[2] = @shortSlot[i] + [-@acrylicThickness,@slotLength,0]
		pts[3] = @shortSlot[i] + [-@acrylicThickness,0,0]
		tab = entities.add_face pts
		tab.pushpull @acrylicThickness
	end
	
	# Fill the upper slots with tabs
	for i in 0...@shortSlot.length
		pts = []
		pts[0] = @shortSlot[i] + [0,0,@areaHeight]
		pts[1] = @shortSlot[i] + [0,0,@areaHeight] + [0,@slotLength,0]
		pts[2] = @shortSlot[i] + [0,0,@areaHeight] + [-@acrylicThickness,@slotLength,0]
		pts[3] = @shortSlot[i] + [0,0,@areaHeight] + [-@acrylicThickness,0,0]
		tab = entities.add_face pts
		tab.pushpull @acrylicThickness
	end
	
	# Turn side material into acrylic
	group.material = @color
	group.material.alpha = @alpha
	
	# Create the other sides
	side2 = group.copy
	t = Geom::Transformation.new([0,0,0], [0,0,1], 180.degrees)
	side2 = side2.move!(t)
	
	# Turn side2 material into acrylic
	side2.material = @color
	side2.material.alpha = @alpha
	
    # End the operation
    model.commit_operation
end

def SOB.main
	SOB.create_top_bottom(0,0,0)
	case @sideType
		when 1
			puts "Interlocking side panel style is selected."
			SOB.create_width_side1()
			SOB.create_length_side1()
		when 2
			puts "Stacked side panel style is selected."
			SOB.create_width_side2()
			SOB.create_length_side2()
		end
	SOB.create_top_bottom(0,0,@areaHeight+@acrylicThickness)
end

def SOB.dialog
	prompts = ["PCB Width (mm)", "PCB Length (mm)", "Circuit Height (mm)", "Acrylic Thickness (mm)", "Side Panel Style"]
	defaults = [String(@pcbWidth/1.m), String(@pcbLength/1.m), String(@areaHeight/1.m), String(@acrylicThickness/1.m), "None"]
	list = ["", "", "", "", "None|Interlocking|Stacked"]
	input = UI.inputbox prompts, defaults, list, "Please enter the box parameters"

	@pcbWidth = Float(input[0]).m
	@pcbLength = Float(input[1]).m
	@areaHeight = Float(input[2]).m
	@acrylicThickness = Float(input[3]).m
	case input[4]
		when "None"
			@sideType = 0
		when "Interlocking"
			@sideType = 1
		when "Stacked"
			@sideType = 2
	end
	
	SOB.main
end

end

plug_menu = UI.menu("Plugins")
plug_menu.add_item("Create a SOB case"){SOB.dialog}
