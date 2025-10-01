FROM debian:stable-slim

# Install dependencies
RUN apt update && apt install -y \
    ncurses-term \
    wget \
    curl \
    git \
    tmux \
    vim

# Set terminal environment variable for proper color detection
ENV TERM=xterm-256color

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

# # copy tmux config to ensure 256-color support
# COPY .tmux.conf /root/.tmux.conf
