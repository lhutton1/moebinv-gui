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
 * \brief METRIC Sets the drawing metric.
 */
const int METRIC = drawingMetric::ELLIPTIC;

/*!
 * \brief POINT_SIZE Sets the size of a point.
 */
const double POINT_SIZE = 3;

/*!
 * \brief LINE_WIDTH Sets the thickness of lines drawn in the scene.
 */
const double LINE_WIDTH = 2;

/*!
 * \brief SCENE_SIZE Sets the size of the scene before it expands.
 */
const int SCENE_SIZE = 300000;

/*!
 * \brief LINE_HOVER_PADDING Sets the extra space to add to a line for hovers.
 */
const int LINE_HOVER_PADDING = 8;

/*!
 * \brief FLOATING_POINT_ACCURACY Adjust the accuracy which coordinates are displayed to.
 */
const int FLOAT_PRECISION = 3;

/*!
 * \brief EPSILON
 */
const double EPSILON = 0.00000001;


#endif // DRAWINGMETRIC_H
