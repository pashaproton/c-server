FROM alpine:latest

RUN apk add --no-cache build-base

WORKDIR /app

COPY . .

RUN gcc -o ./bin/server ./src/*.c

CMD ["./bin/server"]
