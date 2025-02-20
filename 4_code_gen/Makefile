all:
	cd src && $(MAKE) all

make r:
	cd src && $(MAKE) all
	./gen test.tpp
	dot -Tpng tree.dot -o tree.png

clean:
	rm -rf gen tree.dot tree.png test test.ll
	cd src && $(MAKE) clean

dot:
	dot -Tpng tree.dot -o tree.png