#include <string>
#include <iostream>
#include <fstream>

extern "C" {
  #include "libxml/xmlreader.h"
}

int main(int argc, char** argv) {
  // Check if an XML document and RelaxNG schema path are provided
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <XML_FILE> <RNG_FILE>" << std::endl;
    return 1;
  }

  // Read the XML document from file
  std::ifstream xmlFile(argv[1]);
  if (!xmlFile.is_open()) {
    std::cerr << "Failed to open XML file: " << argv[1] << std::endl;
    return 1;
  }

  std::string xmlData((std::istreambuf_iterator<char>(xmlFile)),
                     std::istreambuf_iterator<char>());

  // Read the RelaxNG schema from file
  std::ifstream rngFile(argv[2]);
  if (!rngFile.is_open()) {
    std::cerr << "Failed to open RelaxNG schema file: " << argv[2] << std::endl;
    return 1;
  }

  std::string rngData((std::istreambuf_iterator<char>(rngFile)),
                     std::istreambuf_iterator<char>());

  // Create an XML reader
  xmlTextReaderPtr reader = xmlReaderNewDefault();

  // Parse the XML data
  xmlTextReaderParseString(reader, xmlData.c_str(), xmlData.length());

  // Validate the XML document with the RelaxNG schema
  int result = xmlTextReaderRelaxNGValidate(reader, rngData.c_str());

  if (result == 0) {
    std::cout << "Validation successful" << std::endl;
  } else {
    std::cerr << "Validation failed: " << xmlTextReaderGetError(reader) << std::endl;
  }

  // Free the XML reader
  xmlFree(reader);

  return 0;
}