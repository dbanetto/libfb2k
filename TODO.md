# TODO List

The function or variable is checked once it compiles with the [Foobar2000 Format
Syntax](http://wiki.hydrogenaud.io/index.php?title=Foobar2000:Title_Formatting_Reference)

This is only a basic list of core functions and variables

## Field remappings

### Metadata

- [ ] %album artist%
- [x] %album%
- [x] %artist%
- [ ] %discnumber%
- [ ] %track artist%
- [x] %title%
- [x] %tracknumber%
- [ ] %track number%

### Technical information

- [ ] %bitrate%
- [ ] %channels%
- [ ] %filesize%
- [ ] %filesize_natural%
- [ ] %samplerate%
- [ ] %codec%

- [ ] Special fields

## Control flow

- [x] [...] conditional section
- [x] $if(cond,then)
- [x] $if(cond,then,else)
- [x] $if2(a,else)
- [x] $if3(a1,a2,...,aN,else)
- [ ] $ifequal(n1,n2,then,else)
- [ ] $ifgreater(n1,n2,then,else)
- [ ] $iflonger(s,n,then,else)
- [ ] $select(n,a1,...,aN)

## Arithmetic functions

- [ ] $add(a,b)
- [ ] $div(a,b)
- [ ] $greater(a,b)
- [ ] $max(a,b)
- [ ] $min(a,b)
- [ ] $mod(a,b)
- [ ] $mul(a,b)
- [ ] $muldiv(a,b,c)
- [ ] $rand()
- [ ] $sub(a,b)

## Boolean functions

- [x] $and(...)
- [x] $or(...)
- [x] $not(x)
- [x] $xor(...)

## String functions

- [ ]  $abbr(x)
- [ ]  $abbr(x,len)
- [ ]  $ansi(x)
- [ ]  $ascii(x)
- [ ]  $caps(x)
- [ ]  $caps2(x)
- [ ]  $char(x)
- [ ]  $crc32(a)
- [ ]  $crlf()
- [ ]  $cut(a,len)
- [ ]  $directory(x)
- [ ]  $directory(x,n)
- [ ]  $directory_path(x)
- [ ]  $ext(x)
- [ ]  $filename(x)
- [ ]  $fix_eol(x)
- [ ]  $fix_eol(x,indicator)
- [ ]  $hex(n)
- [ ]  $hex(n,len)
- [ ]  $insert(a,b,n)
- [ ]  $left(a,len)
- [ ]  $len(a)
- [ ]  $len2(a)
- [ ]  $longer(a,b)
- [ ]  $lower(a)
- [ ]  $longest(a,...)
- [ ]  $num(n,len)
- [ ]  $pad(x,len)
- [ ]  $pad_right(x,len)
- [ ]  $pad(x,len,char)
- [ ]  $pad_right(x,len,char)
- [ ]  $padcut(x,len)
- [ ]  $padcut_right(x,len)
- [ ]  $progress(pos,range,len,a,b)
- [ ]  $progress2(pos,range,len,a,b)
- [ ]  $repeat(a,n)
- [ ]  $replace(a,b,c)
- [ ]  $right(a,len)
- [ ]  $roman(n)
- [ ]  $rot13()
- [ ]  $shortest
- [ ]  $strchr(s,c)
- [ ]  $strrchr(s,c)
- [ ]  $strstr(s1,s2)
- [ ]  $strcmp(s1,s2)
- [ ]  $stricmp(s1,s2)
- [ ]  $substr(s,m,n)
- [ ]  $stripprefix(x)
- [ ]  $stripprefix(x,prefix1,prefix2,...)
- [ ]  $swapprefix(x)
- [ ]  $swapprefix(x,prefix1,prefix2,...)
- [ ]  $trim(s)
- [ ]  $tab()
- [ ]  $tab(n)
- [ ]  $upper(s)

## Track info

###  Metadata
- [ ]  $meta(name)
- [ ]  $meta(name,n)
- [ ]  $meta_sep(name,sep)
- [ ]  $meta_sep(name,sep,lastsep)
- [ ]  $meta_test(...)
- [ ]  $meta_num(name)

###  Technical information
- [ ]  $info(name)
- [ ]  $channels()
- [ ]  %replaygain_album_gain%
- [ ]  %replaygain_album_peak%
- [ ]  %replaygain_track_gain%
- [ ]  %replaygain_track_peak%

###  Special fields

- [ ]  %filename%
- [ ]  %filename_ext%
- [ ]  %directoryname%
- [ ]  %last_modified%
- [ ]  %path%
- [ ]  %_path_raw%
- [ ]  %subsong%
- [ ]  %_foobar2000_version%

## Time/Date Functions

- [ ] $year(time)
- [ ] $month(time)
- [ ] $day_of_month(time)
- [ ] $date(time)
- [ ] $time(time)

