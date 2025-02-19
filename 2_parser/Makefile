all:
	cd src && $(MAKE) all

clean:
	rm -rf parser __pycache__ tree.dot tree.png .pytest_cache
	cd src && $(MAKE) clean

dot:
	dot -Tpng tree.dot -o tree.png