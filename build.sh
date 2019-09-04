flex --nounistd -o lex.cpp kasa.l ast.h

cat lex.cpp | awk '{gsub(/register/, "", $0); print $0}' > lex.cpp.bak
mv lex.cpp.bak lex.cpp

make
