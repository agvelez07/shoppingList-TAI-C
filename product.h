#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct product* Product;

// Create a new product with name and type
Product createProduct(const char *name, const char *type);

// Free all memory allocated for the product
void destroyProduct(Product product);

// Getters
const char* getProductName(Product product);
const char* getProductType(Product product);
float getProductMinPrice(Product product);
const char* getProductMinPriceStore(Product product);

// Setters / updates
void setProductName(Product product, const char* newName);
void updateProductPrice(Product product, float newPrice, const char* store);

// Print one product
void printProduct(Product product);

// Print all products from an array
void printAllProducts(Product* product, int listCount);

// Search products by name (partial match) and return indices
int searchProducts(Product* product, int size, const char* searchString, int* foundIndices);

// Print all products that match a given type (partial match)
void printProductsByType(Product* product, int size, const char* searchString, int* foundIndices);

#endif // PRODUCT_H
