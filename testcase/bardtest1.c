#include <string>
#include <iostream>

extern "C" {
  #include "libxml/xmlreader.h"
}

int main() {
  // Create an XML reader
  xmlTextReaderPtr reader = xmlReaderNewDefault();

  // Read the XML data from stdin
  char buffer[1024];
  size_t bytesRead;

  while ((bytesRead = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
    xmlTextReaderParseChunk(reader, buffer, bytesRead, 0);
  }

  // Validate the XML document with the RelaxNG schema
  const char *rng = "";
  int result = xmlTextReaderRelaxNGValidate(reader, rng);

  if (result == 0) {
    std::cout << "Validation successful" << std::endl;
  } else {
    std::cout << "Validation failed" << std::endl;
  }

  // Free the XML reader
  xmlFree(reader);

  return 0;
}