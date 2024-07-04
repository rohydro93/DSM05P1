#include <iostream>
#include <fstream>
#include <limits>
#include "binarySearchTree.h"
#include "product.h"

int main(){
    binarySearchTree<product> products;
    std::ifstream file("products.txt");
    if (!file){
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    
    std::string price, description, productNumber, rating; // read the file line by line, keeping the product details together 
    while (std::getline(file, price) && std::getline(file, description) && std::getline(file, productNumber) && std::getline(file, rating)) 
    {
        //cast price and rating to double
        double priceValue = std::stod(price);
        double ratingValue = std::stod(rating);

        //init product to insert into lists
        product newProduct(priceValue, description, productNumber, ratingValue);
        products.insert(newProduct);
    }
    
    file.close();

    while(true){
        std::cout << "1. Search for a product." << std::endl;
        std::cout << "2. Delete a product." << std::endl;
        std::cout << "3. Exit." << std::endl;

        std::string search;
        int choice;
        std::cin >> choice;
        switch(choice){
            case 1:
                std::cout << "Enter a product number to search for: ";
                std::cin >> search;
                if (products.search(product(0, "", search, 0)))
                    std::cout << "Product found: " << std::endl;
                else
                    std::cout << "Product not found." << std::endl;
                break;
            case 2:
                std::cout << "Enter a product number to delete: ";
                std::cin >> search;
                products.deleteNode(product(0, "", search, 0));
                break;
            case 3:
                products.inorderTraversal();
                return 0;
        }
    }
    return 0;
}