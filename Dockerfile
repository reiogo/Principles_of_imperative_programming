FROM debian:stable-slim

# Install dependencies
RUN apt update && apt install -y \
    wget \
    curl \
    git \
    vim-runtime \
    tmux \
    vim

# Download and install compiler
WORKDIR /cc0
RUN wget https://c0.cs.cmu.edu/downloads/cc0-debian.deb \
    && apt install -y ./cc0-debian.deb \
    && rm cc0-debian.deb

# Install vim-plug
RUN curl -fLo /root/.vim/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim

# Copy .vimrc
COPY .vimrc.build /root/.vimrc
RUN vim +PlugInstall +qall

COPY .vimrc /root/.vimrc
