#!/bin/bash
ruby test.rb > 0.in
./main < 0.in > mo
./quad < 0.in > qo
./fixed < 0.in > fo
echo $(diff mo qo)
echo $(diff mo fo)

