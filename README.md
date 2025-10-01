# Principles_of_imperative_programming
CMU's CS15122 course on C and imperative programming

Build Docker image to make an environment for using cmu's cc0 compiler and coin interpreter

### Docker Commands
Build the image:
    docker build --platform=linux/amd64 -t cmu  .

Run the container, work in the /work directory directly
    docker run -it --rm -v "$PWD":/work --platform=linux/amd64 cmu
