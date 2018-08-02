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

const int metric = drawingMetric::ELLIPTIC;

#endif // DRAWINGMETRIC_H
