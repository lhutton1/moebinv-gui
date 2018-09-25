#ifndef DRAWINGMETRIC_H
#define DRAWINGMETRIC_H

#include <QColor>

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
    ELLIPTIC = 1,
    PARABOLIC = 0,
    HYPERBOLIC = -1
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
    NORELATION,
    ORTHOGONAL,
    FORTHOGONAL,
    DIFFERENT,
    ADIFFERENT,
    REALS,
    TANGENT,
    TANGENT_I,
    TANGENT_O,
    STEINER_POWER,
    CYCLE_ANGLE,
    CYCLE_CROSS_T_DISTANCE,
    PRODUCT_SIGN,
    CYCLE_MOBIUS,
    CYCLE_SL2
};

enum params {
    NO_PARAMS,
    SINGLE_PARAM,
    MATRIX_4,
    MATRIX_8,
    PRODUCT_COMBOBOX
};

enum evalType {
  FLOATING,
  EXACT
};

/*!
 * \brief EPSILON Point at which a number is taken to be 0 due to rounding errors
 */
const double EPSILON = 0.00000001;

enum asyLineStyle {
    SOLID,
    DASHED,
    DOTTED
};

struct cycleStyleData {
    QColor colour;
    double lineWidth;
    int lineStyle;
};


#endif // DRAWINGMETRIC_H
