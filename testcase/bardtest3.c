#include <libxml/parser.h>
#include <libxml/relaxng.h>
#include <stdio.h>

int main() {
  xmlRelaxNGParserCtxtPtr ctxt = xmlRelaxNGNewParserCtxt();

  // Set the input schema definition resource
  const char *schema = "<?xml version=\"1.0\"?>\n"
                       "<grammar xmlns=\"http://relaxng.org/ns/relaxng\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://relaxng.org/ns/relaxng http://relaxng.org/nsg/relaxng.rng\">\n"
                       "  <element name=\"doc\">\n"
                       "    <element name=\"title\" type=\"string\"/>\n"
                       "    <element name=\"body\" type=\"string\"/>\n"
                       "  </element>\n"
                       "</grammar>\n";

  // Set the schema resource URL
  ctxt->URL = BAD_CAST "http://example.com/schema.rng";

  // Parse the schema definition resource
  xmlRelaxNGPtr schemaPtr = xmlRelaxNGParse(ctxt);
  if (schemaPtr == NULL) {
    fprintf(stderr, "Error parsing schema: %s\n", ctxt->err);
    return 1;
  }

  // Validate an XML document against the parsed schema
  xmlDocPtr doc = xmlReadFile("document.xml", NULL, 0);
  if (doc == NULL) {
    fprintf(stderr, "Error reading document: %s\n", xmlGetLastError());
    return 1;
  }

  int result = xmlRelaxNGValidate(doc, schemaPtr, ctxt);
  if (result == XML_RNG_VALID) {
    printf("Document is valid\n");
  } else if (result == XML_RNG_INVALID) {
    printf("Document is invalid: %s\n", ctxt->err);
  } else {
    printf("Error validating document: %s\n", ctxt->err);
    return 1;
  }

  // Free resources
  xmlRelaxNGFree(schemaPtr);
  xmlFreeDoc(doc);
  xmlRelaxNGFreeParserCtxt(ctxt);

  return 0;
}