#ifndef DRAWINGMETRIC_H
#define DRAWINGMETRIC_H

/*!
 * \brief drawingMetric enum
 *
 * 3-types of drawing metric:
 *      elliptic - ...
 *      parabolic - ...
 *      hyperbolic - ...
 */
enum drawingMetric {
    ELLIPTIC,
    PARABOLIC,
    HYPERBOLIC
};

/*!
 * \brief metric
 *
 * Sets the drawing metric. By default this is Elliptic.
 */
const int metric = drawingMetric::ELLIPTIC;

enum relationType {
    ORTHOGONAL,
    FORTHOGONAL,
    TANGENT,
    DIFFERENT
};

#endif // DRAWINGMETRIC_H
