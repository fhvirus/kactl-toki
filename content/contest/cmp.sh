#!/usr/bin/env bash
set -e
while :; do
  python3 gen.py > input
  diff -y <(./bru < input) <(./sol < input)
done
