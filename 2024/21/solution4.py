import fileinput, functools

n = [ "789", "456", "123", " 0A" ]
d = [ " ^A", "<v>" ]

def path( p, f, t ):
    fx, fy = next( ( x, y ) for y, r in enumerate( p ) for x, c in enumerate( r ) if c == f )
    tx, ty = next( ( x, y ) for y, r in enumerate( p ) for x, c in enumerate( r ) if c == t )
    def g( x, y, s ):
        if ( x, y ) == ( tx, ty ):             yield s + 'A'
        if tx < x and p[ y ][ x - 1 ] != ' ': yield from g( x - 1, y, s + '<' )
        if ty < y and p[ y - 1 ][ x ] != ' ': yield from g( x, y - 1, s + '^' )
        if ty > y and p[ y + 1 ][ x ] != ' ': yield from g( x, y + 1, s + 'v' )
        if tx > x and p[ y ][ x + 1 ] != ' ': yield from g( x + 1, y, s + '>' )
    return min( g( fx, fy, "" ),
                key = lambda p: sum( a != b for a, b in zip( p, p[ 1 : ] ) ) )

@functools.cache
def solve( s, l ):
    if l > 25: return len( s )
    return sum( solve( path( d if l else n, f, t ), l + 1 ) for f, t in zip( 'A' + s, s ) )

print( sum( solve( s.strip(), 0 ) * int( s[ : 3 ] )
            for s in fileinput.input() ) )
