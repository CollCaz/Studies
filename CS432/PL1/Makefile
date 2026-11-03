all:
	flex lexer.l
	gcc lex.yy.c
	./a.out lexer_test.pli 2>&1

clean:
	rm -f lex.yy.c a.out
