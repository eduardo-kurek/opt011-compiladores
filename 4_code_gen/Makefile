all:
	cd src && $(MAKE) all

make r:
	cd src && $(MAKE) all
	./gen test.tpp
	dot -Tpng tree.dot -o tree.png

dot:
	dot -Tpng tree.dot -o tree.png