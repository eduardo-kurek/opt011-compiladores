all:
	cd src && $(MAKE) all

# Compila e executa com o arquivo de teste test.tpp
make r:
	cd src && $(MAKE) all
	./sem test.tpp
	dot -Tpng tree.dot -o tree.png

clean:
	rm -rf sem __pycache__ tree.dot tree.png .pytest_cache
	cd src && $(MAKE) clean

dot:
	dot -Tpng tree.dot -o tree.png	