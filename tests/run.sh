#!/bin/sh
set -e
f=$(mktemp)
printf 'hello world\nfoo  bar baz\n\nlast' >"$f"

l=$(wc -l <"$f")
w=$(wc -w <"$f")
c=$(wc -c <"$f")

out=$(./word-counter "$f")
echo "$out" | grep -Eq "^lines: $l *$" || {
  echo "FAIL lines"
  exit 1
}
echo "$out" | grep -Eq "^words: $w *$" || {
  echo "FAIL words"
  exit 1
}
echo "$out" | grep -Eq "^bytes: $c *$" || {
  echo "FAIL bytes"
  exit 1
}

out=$(./word-counter -l "$f")
echo "$out" | grep -q "bytes" && {
  echo "FAIL -l shows bytes"
  exit 1
}

out=$(./word-counter "$f" "$f")
echo "$out" | grep -q "^total$" || {
  echo "FAIL total"
  exit 1
}

rm "$f"
echo ok
