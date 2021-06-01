/** @file
 * @brief Interface to communicate with Flask server.
 *
 * @author Jakub Jurasz, Konrad Owsikowski
 * @date 28.04.2021
 */
#ifndef API_H
#define API_H

#include <string>

/** @brief Returns new FEN string.
 * Returns new FEN string after move validation and making computer's turn.
 * @param[in] fenString -	a FEN string representing current game state
 * @param[in] i_old     - previous player's x position
 * @param[in] j_old     - previous player's y position
 * @param[in] i_new     - new player's x position
 * @param[in] j_new     - new player's y position
 * @return FEN string representing game state after computer's turn.
 */
std::string getNextFen(std::string fenString, int i_old, int j_old, int i_new, int j_new);

#endif // API_H