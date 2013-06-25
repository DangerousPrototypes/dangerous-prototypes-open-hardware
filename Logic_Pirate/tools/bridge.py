import serial, socket, time

COM = 'COM24'
BAUD = 1000000
HOST = 'localhost'
PORT = 8000
SIZE = 4096

def hexify( d ):
    result = []
    for byte in d:
        result.append( '$%s' % hex( ord( byte ) )[ 2 : ].zfill( 2 ).upper() )
    return ' '.join( result )

while True:
    s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
    s.bind( ( HOST, PORT ) )
    print 'listening on port %s' % PORT
    s.listen( 1 )
    conn, address = s.accept()
    print 'connected'
    conn.setblocking( 0 )
    start = time.time()

    ser = serial.Serial( COM, BAUD, timeout=0 )
    while True:
        try:
            d = conn.recv( SIZE )
        except socket.error, e:
            time.sleep( 0.0001 )
        else:
            if len( d ) > 0:
                print 'socket->serial (%s)' % len( d ), hexify( d )
                ser.write( d )
            else:
                end = time.time()
                print end - start, 's'
                print 'disconnected'
                print
                ser.close()
                break

        d = ser.read( SIZE )
        if len( d ) > 0:
            print 'socket<-serial (%s)' % len( d ), '"%s"' % d if len( d ) < SIZE else ''
            conn.send( d )
