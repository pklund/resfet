/**
 * @file luna_visitor.hpp
 * @author Andrew Obler (ajo2@rice.edu)
 * @author Tommy Yuan (ty19@rice.edu)
 * @brief Visitor for processing received commands 
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 */

#ifndef WORKER_VISITOR_HPP
#define WORKER_VISITOR_HPP

#include <stdint.h>

#include "commands/tcp_commands.hpp"

extern int engine_type;
extern int time_between_gitvc;
extern int gitvc_wait_time;
extern int pressure_min;
extern int pressure_max;
extern int preignite_us;
extern int hotflow_us;
extern bool ignition_on;
extern bool use_gitvc;
extern std::vector<uint8_t> gitvc_times;

/**
 * @brief Defines the superclass for the Luna and Titan visitors.
 * 	  A visitor "visits" a received command performs the appropriate
 *	  task based on the command type.
 * 	  Based on a design by Arne Mertz.
 *        See https://arne-mertz.de/2016/04/visitor-pattern-part-2-enum-based-visitor/
 */
class worker_visitor {
    public:
	/**
	 * @brief Whether the ignition sequence is currently enabled.
	 */
        bool burn_on;

        /**
         * @brief Selects the correct task for the given work queue item and its queue,
         * 	  and performs it.
         */
        void visit(work_queue_item& item);

	/**
	 * @brief Visits a command by performing the function associated
	 * 	  with that command.
	 */
        void visitCommand(COMMAND c) override;

        /**
         * @brief Operation corresponding to the beginning of ignition. 
         */
        virtual void visitIgn(work_queue_item&);

        /**
         * Operation for an unknown/unspecified action.
         */
        void visitDefault(work_queue_item&);

        worker_visitor() : qw(qw), qn(qn), adcs(adcs), nw_ref(nw_ref)
                        , start_time_nitr(0)
                        , pressure_avg(700)
                        , burn_on(false)
        {
        }

        ~worker_visitor() = default;

        void check_ti_list(timestamp_t t, safe_queue<work_queue_item> &qw);
};

#endif // WORKER_VISITOR_HPP
