int get_current_direction();

void set_current_direction(int direction);

int get_queue(int floor);

void set_queue(int floor, int order);

void set_order_up();

void set_order_down();

void set_order_inside();

void handle_orders();

int check_orders_above(int starting_point);

int check_orders_below(int starting_point);

int get_order_count();

void update_current_direction();

int check_up_at_floor();

int check_down_at_floor();

int check_both_or_inside_at_floor();

int check_arrival();

void clear_all_orders();

void print_all_orders();
