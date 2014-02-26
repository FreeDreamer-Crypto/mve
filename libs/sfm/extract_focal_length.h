/*
 * Database to extract the focal length from an image's EXIF tags.
 * Written by Simon Fuhrmann.
 */

#ifndef SFM_EXTRACT_FOCAL_LENGTH_HEADER
#define SFM_EXTRACT_FOCAL_LENGTH_HEADER

#include <utility>

#include "mve/image_exif.h"
#include "sfm/defines.h"

SFM_NAMESPACE_BEGIN

/**
 * Indicator which focal length estimation has been used.
 */
enum FocalLengthMethod
{
    FOCAL_LENGTH_AND_DATABASE,
    FOCAL_LENGTH_35MM_EQUIV,
    FOCAL_LENGTH_DEFAULT_VALUE
};

/**
 * Extracts the focal length from the EXIF tags of an image.
 *
 * The algorithm first checks for the availability of the "focal length"
 * in EXIF tags and computes the effective focal length using a database
 * of camera sensor sizes. If the camera model is unknown to the database,
 * the "focal length 35mm equivalent" EXIF tag is used. If this information
 * is also not available, a default value is used.
 *
 * This estimation can fail in numerous situations:
 *  - The image contains no EXIF tags (default value is used)
 *  - The camera did not specify the focal length in EXIF
 *  - The lens specifies the wrong focal length due to lens incompatibility
 *  - The camera is not in the database and the 35mm equivalent is missing
 *  - The camera used digial zoom changing the effective focal length
 *
 * The resulting focal length is in normalized format, that is the quotient
 * of the image focal length by the sensor size. E.g. a photo taken at 70mm
 * with a 35mm sensor size will result in a normalized focal length of 2.
 */
std::pair<float, FocalLengthMethod>
extract_focal_length (mve::image::ExifInfo const& exif);

SFM_NAMESPACE_END

#endif /* SFM_EXTRACT_FOCAL_LENGTH_HEADER */
