FROM debian:stable-slim

# Install dependencies
RUN apt update && apt install -y \
    wget \
    vim 

# Download and install C0 compiler
WORKDIR /c0
RUN wget https://c0.cs.cmu.edu/downloads/cc0-debian.deb \
    && apt install -y ./cc0-debian.deb \
    && rm cc0-debian.deb


