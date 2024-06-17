import threading

# this process takes the serial port, the output queues that is shared with the DMRS model and traffic model and lane model and the speed variable that is shared with the STM process
def warning_process(dmrs_output_queue, traffic_output_queue, lane_output_queue, display_output_queue, speed , trip_statistics):

    # Define a function to handle the DMRS output queue
    def handle_dmrs_output(dmrs_output_queue):
        while True:
            # Get data from the DMRS output queue
            data = dmrs_output_queue.get()


            # Assuming your predictions are numerical labels (1, 2, 3, 4, 5)
                # You can map them to the corresponding actions
                # predicted_actions = {
                #     1: 'sudden_acceleration',
                #     2: 'sudden_right_turn',
                #     3: 'sudden_left_turn',
                #     4: 'sudden_break',
                #     5: 'Normal'
                # }
            
            if data == 1:
                trip_statistics.increment_sudden_acceleration()

            if data == 2:
                trip_statistics.increment_agg_tr()
            
            if data == 3:
                trip_statistics.increment_agg_tl()

            if data == 4:
                trip_statistics.increment_sudden_brake()

            if data == 5:
                trip_statistics.increment_normal_driving()
            
            # # Example: Print the data
            # print("DMRS Output:", data)

    # Define a function to handle the traffic output queue
    def handle_traffic_output(traffic_output_queue):
        while True:
            # Get data from the traffic output queue
            data = traffic_output_queue.get()
            
            # TODO: compare the speed with the speed limit and increment the speed limit violation
            if data == 'speed_limit_violation':
                trip_statistics.increment_speed_limit_violation()

            # TODO: Send the output to the STM
            
            # Example: Print the data
            print("Traffic Output:", data)

    # Define a function to handle the lane output queue
    def handle_lane_output(lane_output_queue):
        while True:
            # Get data from the lane output queue
            data = lane_output_queue.get()
            
            if data == False:
                # TODO: Send the warning to the STM
                pass
            
            # Example: Print the data
            print("Lane Output:", data)

    # Create and start the threads
    dmrs_thread = threading.Thread(target=handle_dmrs_output, args=(dmrs_output_queue,))
    traffic_thread = threading.Thread(target=handle_traffic_output, args=(traffic_output_queue,))
    lane_thread = threading.Thread(target=handle_lane_output, args=(lane_output_queue,))

    dmrs_thread.start()
    traffic_thread.start()
    lane_thread.start()

    