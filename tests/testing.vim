let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
doautoall SessionLoadPre
silent only
silent tabonly
cd ~/Documents/school/nandtotetris/chapter6/assembler/tests
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
set shortmess+=aoO
badd +5 parser_test.cpp
badd +3 ~/Documents/school/nandtotetris/chapter6/assembler/src/Parser.cpp
badd +14 ~/Documents/school/nandtotetris/chapter6/assembler/CMakeLists.txt
badd +1 CMakeLists.txt
argglobal
%argdel
$argadd parser_test.cpp
edit parser_test.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 57 + 86) / 173)
exe 'vert 2resize ' . ((&columns * 57 + 86) / 173)
exe 'vert 3resize ' . ((&columns * 57 + 86) / 173)
tcd ~/Documents/school/nandtotetris/chapter6/assembler
argglobal
balt ~/Documents/school/nandtotetris/chapter6/assembler/src/Parser.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 5 - ((4 * winheight(0) + 28) / 56)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 5
normal! 02|
wincmd w
argglobal
if bufexists(fnamemodify("~/Documents/school/nandtotetris/chapter6/assembler/tests/CMakeLists.txt", ":p")) | buffer ~/Documents/school/nandtotetris/chapter6/assembler/tests/CMakeLists.txt | else | edit ~/Documents/school/nandtotetris/chapter6/assembler/tests/CMakeLists.txt | endif
if &buftype ==# 'terminal'
  silent file ~/Documents/school/nandtotetris/chapter6/assembler/tests/CMakeLists.txt
endif
balt ~/Documents/school/nandtotetris/chapter6/assembler/CMakeLists.txt
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 7 - ((6 * winheight(0) + 28) / 56)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 7
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("~/Documents/school/nandtotetris/chapter6/assembler/CMakeLists.txt", ":p")) | buffer ~/Documents/school/nandtotetris/chapter6/assembler/CMakeLists.txt | else | edit ~/Documents/school/nandtotetris/chapter6/assembler/CMakeLists.txt | endif
if &buftype ==# 'terminal'
  silent file ~/Documents/school/nandtotetris/chapter6/assembler/CMakeLists.txt
endif
balt ~/Documents/school/nandtotetris/chapter6/assembler/tests/CMakeLists.txt
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 14 - ((13 * winheight(0) + 28) / 56)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 14
normal! 021|
wincmd w
2wincmd w
exe 'vert 1resize ' . ((&columns * 57 + 86) / 173)
exe 'vert 2resize ' . ((&columns * 57 + 86) / 173)
exe 'vert 3resize ' . ((&columns * 57 + 86) / 173)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
