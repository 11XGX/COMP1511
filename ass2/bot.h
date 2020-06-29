/************************************************************************
* FILENAME:
*		bot.h
*
* DESCRIPTION(S):
*		This is the header file for my trader bot, which contains all
*		of the function prototypes and defined values used by my program.
*
* AUTHOR:
*		Nathan Ellis
*
* OTHER AUTHOR INFORMATION:
*		zID - z5160405
*		email - z5160405@students.unsw.edu.au
*
* COMPLETION DATE:
*		04 June 2017
*
************************************************************************/

#define MAX_VALUE 999999999
#define SELLER_NAME 0
#define BUYER_NAME 1
#define SELLER_PRICE 0
#define BUYER_PRICE 1
#define SELLER_QUANTITY 0
#define BUYER_QUANTITY 1

int find_closest_fuel(struct bot *b);

int find_fuel_price(struct bot *b, int fuelDistance);

void find_seller_names(struct bot *b, char * sellerNames[MAX_LOCATIONS]);

void find_seller_commodity_names(struct bot *b, char * sellerNames[MAX_LOCATIONS], char * commodityNames[MAX_LOCATIONS]);

void find_relevant_buyer_names(struct bot *b, char * sellerNames[MAX_LOCATIONS], char * commodityNames[MAX_LOCATIONS], char * locationNames[MAX_LOCATIONS][2]);

void find_location_information(struct bot *b, char * locationNames[MAX_LOCATIONS][2], int prices[MAX_LOCATIONS][2], int quantities[MAX_LOCATIONS][2], int cargoWeights[MAX_LOCATIONS], int cargoVolumes[MAX_LOCATIONS]);

void find_distance_information(struct bot *b, char * locationNames[MAX_LOCATIONS][2], int sellerDistances[MAX_LOCATIONS], int buyerDistances[MAX_LOCATIONS], int tripDistances[MAX_LOCATIONS]);

void find_full_trip_costs(struct bot *b, int fuelPrice, int tripDistances[MAX_LOCATIONS], int fullTripCosts[MAX_LOCATIONS]);

void order_location_names(struct bot *b, char * locationNames[MAX_LOCATIONS][2], int prices[MAX_LOCATIONS][2], int quantities[MAX_LOCATIONS][2], int cargoWeights[MAX_LOCATIONS], int cargoVolumes[MAX_LOCATIONS], int sellerDistances[MAX_LOCATIONS], int buyerDistances[MAX_LOCATIONS], int tripDistances[MAX_LOCATIONS], int fullTripCosts[MAX_LOCATIONS], char * orderedLocationNames[MAX_LOCATIONS][2]);

int find_expected_buying_quantity(struct bot *b, int sellerDistance, int cargoWeights[MAX_LOCATIONS], int cargoVolumes[MAX_LOCATIONS], int prices[MAX_LOCATIONS][2], int quantities[MAX_LOCATIONS][2]);

int find_buyer_from_cargo(struct bot *b);

int find_closest_dump(struct bot *b);
