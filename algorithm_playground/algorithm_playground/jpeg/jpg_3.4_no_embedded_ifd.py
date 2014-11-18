import struct

DEBUG = 1
def debug(*debug_string):
    '''used to print style debugging.
'''
    if DEBUG:       
        for each in debug_string:
            print(each, end="")
        print(end="\n")

BYTE = 1
ASCII = 2
SHORT = 3
LONG = 4
RATIONAL = 5

def parse_ffe1_frag(frag):

    unpack = struct.unpack
    
    #frag[0:1] ffe1
    if frag[1] != 0xe1:
        debug(frag[0], frag[1])
        print("error input")
        return
    length = unpack('>H', frag[2:4])[0]
    debug('length = ', length)
    
    frag = frag[4:]
    exif = struct.unpack('6s', frag[:6])[0]
    debug("exif = ", exif)
    exif = exif.strip(b'\0')
    debug(exif)
    if exif != b"Exif":
        raise "Bad Exif Marker."

    tiff = frag[6:]#start from 6
    tiff_endian = tiff[:2]
    e = ''
    debug(tiff_endian)
    if tiff_endian == b"II":
        e = '<'
    elif tiff_endian == b"MM":
        e = '>'
    tiff_tag = struct.unpack(e+"H", tiff[2:4])[0]
    offset = struct.unpack(e+"I", tiff[4:8])[0]  
    debug("tiff_tag = ",tiff_tag, ", tiff_off = ", offset)

    #ifd_data = tiff[tiff_off:]
    #ifd_num = struct.unpack(e+"H", ifd_data[:2])[0]
    
    while offset:
        ifd_num = unpack(e+"H", tiff[offset:offset+2])[0]
        debug("number of directory entries = ", ifd_num)
        k=0

        next_start = offset + 2 + ifd_num * 12
        next_offset = struct.unpack(e+'I', tiff[next_start : next_start+4])[0]
        debug('==> OFFSET %d - %d' % (offset, next_offset))

        while k < ifd_num:
            start = 2 + k * 12 + offset
            entry = struct.unpack(e + 'HHII', tiff[start:start+12])
            t_tag, t_type, t_count, t_value = entry
            debug("tag=%d,type=%d,count=%d,value=%d" % (t_tag, t_type, t_count, t_value))

            if t_type == ASCII:
                if t_count == 4:
                    actual_data = tiff[start+8:start+12].decode()
                else:
                    the_data = tiff[t_value:t_value+t_count]
                    if the_data[-1] != b'0x0':
                        actual_data = the_data + b'0x0'
                    actual_data = the_data.decode()
                    
                debug(' actual_data = ', actual_data)                    
                
            k += 1
        
        offset = next_offset
    
def strip_exif(img, tag):
    beg_exif = img.find(tag)
    if beg_exif < 0:
        return

    print(beg_exif)
    
    ret = img[0:beg_exif]
    print(ret)

    # call parse.
    parse_ffe1_frag(img[beg_exif:])

    debug('-------------------------------------')
    
    size_bs = img[beg_exif+2 : beg_exif+4]
    print(size_bs)
    
    exif_size = struct.unpack('>H', size_bs)[0]
    print(exif_size)
    
    next_frag = img[beg_exif + 2 + exif_size:]
    #print(next_frag[0:2], next_frag[2:4])

    return ret + next_frag

# f = open('IMG_9799_Small.jpg', 'rb')
f = open('IMG_20141118_084120.jpg', 'rb')
img = f.read()
f.close()

# tag = b'\xff\xe0'
tag = b'\xff\xe1'
tmp = strip_exif(img, tag)
f = open('output.jpg', 'wb')
f.write(tmp)
f.close()

tags = { 
        0x0: ("GPS tag version", "GPSVersionID", BYTE, 4), 
        0x1: ("North or South Latitude", "GPSLatitudeRef", ASCII, 2), 
        0x2: ("Latitude", "GPSLatitude", RATIONAL, 3), 
        0x3: ("East or West Longitude", "GPSLongitudeRef", ASCII, 2), 
        0x4: ("Longitude", "GPSLongitude", RATIONAL, 3), 
        0x5: ("Altitude reference", "GPSAltitudeRef", BYTE, 1), 
        0x6: ("Altitude", "GPSAltitude", RATIONAL, 1) 
        }
tag = 1
print( tags.get(tag, (hex(tag), 0))[0] )
# print( tags.get(hex(tag))[0] )
print( type(tags) )


