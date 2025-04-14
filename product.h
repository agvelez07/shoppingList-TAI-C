#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct product* Product;

Product createProduct(const char* name, const char* type);

void destroyProduct(Product product);
const char* getProductName(Product product);
const char* getProductType(Product product);
float getProductMinPrice(Product product);
const char* getProductMinPriceStore(Product product);
void setProductName(Product product, const char* newName);
void updateProductPrice(Product product, float newPrice, const char* store);
void printProduct(Product product);
int searchProducts(Product* products, int size, const char* searchString, int* foundIndices);
int printProductsByType(Product* products, int size, const char* searchString, int* foundIndices);

#endif // PRODUCT_H
