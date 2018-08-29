#ifndef DRAWINGMETRIC_H
#define DRAWINGMETRIC_H

/*
 * This file contains settings and configuration variables for the application.
 */

/*!
 * \brief drawingMetric enum
 *
 * 3-types of drawing metric:
 *      elliptic - Draw cycles using points, lines and circles
 *      parabolic - ...
 *      hyperbolic - ...
 */
enum drawingMetric {
    ELLIPTIC,
    PARABOLIC,
    HYPERBOLIC
};

/*!
 * \brief relationType enum
 *
 * Defines the different possible relations.
 *
 *      orthogonal - ...
 *      forthogonal - ...
 *      tangent - ...
 *      different - ...
 */
enum relationType {
    ORTHOGONAL,
    FORTHOGONAL,
    TANGENT,
    DIFFERENT
};

/*!
 * \brief EPSILON Point at which a number is taken to be 0 due to rounding errors
 */
const double EPSILON = 0.00000001;


#endif // DRAWINGMETRIC_H
