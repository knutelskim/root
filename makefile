DOCDIR := doc
TARGET := fitowanie.cpp

.PHONY: run-fit clean doc

doc:
	doxygen Doxyfile		

clean:
	-rm -rf $(DOCDIR)
	-rm -f *.txt
	-rm -f *.pdf
	-rm -f *.save

run-fit: $(TARGET)
	root -l $(TARGET)
