# Multi-stage build for CasseBriques
# Stage 1: Build
FROM ubuntu:22.04 as builder

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libsfml-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN mkdir -p build && cd build && \
    cmake .. && \
    cmake --build .

# Stage 2: Runtime
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    libsfml-graphics2.5 \
    libsfml-window2.5 \
    libsfml-system2.5 \
    libx11-6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build/CasseBriques /app/CasseBriques

# Enable X11 forwarding for GUI
ENV DISPLAY=:0

CMD ["./CasseBriques"]
