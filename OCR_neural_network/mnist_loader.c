#include "mnist.h"

int main_mnist(int argc, char *argv[])
{   
    load_mnist();
    if (argc < 3)
    {
        for (size_t i = 0; i < 100; i++)
        {
            save_mnist_pgm(train_image, i, train_label[i], 0);
        }

        for (size_t j = 0; j < 20; j++)
        {
            save_mnist_pgm(test_image, j, test_label[j], 1);
        }
    }
    else
    {
        if (strcmp(argv[2], "-train") == 0)
        {
            for (size_t i = 0; i < 100; i++)
            {
                save_mnist_pgm(train_image, i, train_label[i], 0);
            }
        }
        else    
        {
            for (size_t j = 0; j < 20; j++)
            {
                save_mnist_pgm(test_image, j, test_label[j], 1);
            }
        }
    }

    return 0;
}
