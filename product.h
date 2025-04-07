#ifndef PRODUCT_H
#define PRODUCT_H

// Opaque type definition
typedef struct product* Product;

// Public API
Product createProduct(const char *name, const char *type);
void destroyProduct(Product product);

const char* getProductName(Product product);
const char* getProductType(Product product);
float getProductMinPrice(Product product);
const char* getProductMinPriceStore(Product product);

void setProductName(Product product, const char* newName);
void updateProductPrice(Product product, float newPrice, const char* store);
void printProduct(Product product);

#endif // PRODUCT_H
