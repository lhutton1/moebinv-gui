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
 * \brief SCENE_SIZE Sets the size of the scene before it expands.
 */
const int SCENE_SIZE = 300000;

/*!
 * \brief LINE_HOVER_PADDING Sets the extra space to add to a line for hovers.
 */
const int LINE_HOVER_PADDING = 8;

/*!
 * \brief ZOOM_FACTOR Zoom factor for zooming in and out of the scene
 */
const int ZOOM_FACTOR = 1.0015;

#endif // DRAWINGMETRIC_H
