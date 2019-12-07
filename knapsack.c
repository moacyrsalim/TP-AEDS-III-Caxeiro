//http://www.martinbroadhurst.com/unbounded-knapsack-using-dynamic-programming-in-c.html
struct knapsack {
    unsigned int profit;
    struct knapsack *prev;
};
typedef struct knapsack knapsack;
 
/* Find the minimum weight item with this profit */
int min_weight_item(unsigned int profit, const unsigned int *weights,
        const unsigned int *profits, size_t len)
{
    int item = -1;
    unsigned int i;
    for (i = 0; i < len; i++) {
        if (profits[i] == profit) {
            if (item == -1 || weights[i] < weights[item]) {
                item = i;
            }
        }
    }
    return item;
}
 
unsigned int unbounded_knapsack(unsigned int capacity, unsigned int *weights,
        unsigned int *profits, unsigned int *counts, size_t len)
{
    knapsack *z = malloc((capacity + 1) * sizeof(knapsack));
    unsigned int c, i;
    unsigned int solution, profit;
    z[0].profit = 0;
    z[0].prev = NULL;
    knapsack *current;
    /* Fill in the array */
    for (c = 1; c <= capacity; c++) {
        z.profit = z.profit;
        z.prev = &(z);
        for (i = 0; i < len; i++) {
            if (weights[i] <= c) {
                /* prev is the best knapsack without adding this item */
                knapsack *prev = z + (c - weights[i]);
                if (prev->profit + profits[i] > z.profit) {
                    z.profit = prev->profit + profits[i];
                    z.prev = prev;
                }
            }
        }
    }
    /* Read back the best solution */
    for (profit = z[capacity].profit, current = z[capacity].prev;
            current != NULL;
            profit = current->profit, current = current->prev) {
        counts[min_weight_item(profit - current->profit, weights, profits, len)]++;
         
    }
    solution = z[capacity].profit;
    free(z);
    return solution;
}