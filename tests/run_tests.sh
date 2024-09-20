#!/bin/bash

cd "$(dirname "$0")/.."
make all
make test
