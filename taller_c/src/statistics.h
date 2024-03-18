#ifndef STATISTICS_H
#define STATISTICS_H

/** Documentacion Doxygen
 * @brief Constructor
 * 
 * @details
 * @code
 *  
 * @endcode
 * @param
 * @return
 * @remark
 * 
*/

// Declaracion del atributo privado
typedef struct statistics statistics_t;

statistics_t* statistics_create(void);
int statistics_run(statistics_t *statistics, int argc, char* argv[]);
void statistics_destroy(statistics_t *statistics);


#endif // STATISTICS_H 