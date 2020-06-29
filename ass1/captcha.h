int read_pbm(char filename[], int height, int width, int pixels[height][width]);

int get_pbm_dimensions(char filename[], int *height, int *width);

void distinguish_digit(int height, int width, int pixels[height][width]);

void print_image(int height, int width, int pixels[height][width]);

void get_bounding_box(int height, int width, int pixels[height][width], int *start_row, int *start_column, int *box_height, int *box_width);

void copy_pixels(int height, int width, int pixels[height][width], int start_row, int start_column, int copy_height, int copy_width, int copy[copy_height][copy_width]);

double get_horizontal_balance(int height, int width, int pixels[height][width]);

double get_vertical_balance(int height, int width, int pixels[height][width]);

int get_holes(int height, int width, int pixels[height][width]);

int get_bottom_hole_location(int height, int width, int pixels[height][width]);

int get_top_hole_location(int height, int width, int pixels[height][width]);

int get_max_vertical_intersections(int height, int width, int pixels[height][width]);

int get_one_check(int height, int width, int pixels[height][width]);

int get_three_check1(int height, int width, int pixels[height][width]);

int get_three_check2(int height, int width, int pixels[height][width]);

int get_four_check(int height, int width, int pixels[height][width]);

int get_five_check(int height, int width, int pixels[height][width]);

int get_seven_check(int height, int width, int pixels[height][width]);
