set tabstop=2
set shiftwidth=2
set expandtab
set number
set rnu
syntax on
autocmd Filetype cpp map <F5> :w<CR>:!echo "\033[48;05;56m\n\n\n\n\033[m\n";g++ % -o %< -std=c++20 -O1 && time ./%< <CR>
autocmd Filetype rust map <F5> :w<CR>:!echo "\033[48;05;56m\n\n\n\n\e[m\n";rustc % && time ./%< <CR>
set si
