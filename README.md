# Principles_of_imperative_programming
CMU's CS15122 course on C and imperative programming

Using CMU's interpreter: coin, or compiling the program with CMU's compiler: cc0.
Build Docker image in order to use coin and cc0.

### Docker Commands
Build the image:
    docker build --platform=linux/amd64 -t cmu  .

Run the container, work in the /work directory directly
    docker run -it --rm -v "$PWD":/work --platform=linux/amd64 cmu
