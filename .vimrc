" Plugins will be downloaded under the specified directory.
call plug#begin(has('nvim') ? stdpath('data') . '/plugged' : '~/.vim/plugged')

" Declare the list of plugins.
Plug 'joshdick/onedark.vim'
Plug 'sbdchd/neoformat'

" List ends here. Plugins become visible to Vim after this call.
call plug#end()


" Theme settings
" let g:airline_theme='onedark'
" colorscheme onedark
" set background=dark " for the dark version
colorscheme onedark 

" Prettier settings
autocmd BufWritePre *.js Neoformat


" Non plugin settings:
set whichwrap=<,>,h,l

set tabstop=2
set softtabstop=2
" when indenting with '>', use 2 spaces width
set shiftwidth=2

let &t_SI = "\e[5 q"
let &t_EI = "\e[2 q"

" turn hybrid line numbers on
:set number relativenumber
:set nu rnu
