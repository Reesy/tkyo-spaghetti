FROM node:stretch-slim

EXPOSE 3000

COPY ./embuild/resources ./embuild/resources

COPY ./embuild/index.html  \
     ./embuild/sam_icon_2.png \ 
     ./embuild/TkyoSpaghetti.data \
     ./embuild/TkyoSpaghetti.js \
     ./embuild/TkyoSpaghetti.wasm \
     ./embuild

RUN npm install -g serve

CMD ["serve", "-s", "./embuild"]