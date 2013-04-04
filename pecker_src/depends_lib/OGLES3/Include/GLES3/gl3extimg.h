#ifndef __gl3extimg_h_
#define __gl3extimg_h_

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*
 * IMG extension tokens
 *------------------------------------------------------------------------*/

/* GL_IMG_binary_shader */
#ifndef GL_IMG_binary_shader
#define GL_SGX_BINARY_IMG	0x8C0A
/* TODO: Add proper value for RGX binaries */
#define GL_RGX_BINARY_IMG	0x0
#endif

/* GL_IMG_texture_format_BGRA8888 */
#define GL_BGRA							0x80E1

/*------------------------------------------------------------------------*
 * IMG extension functions
 *------------------------------------------------------------------------*/

/* GL_IMG_binary_shader */
#ifndef GL_IMG_binary_shader
#define GL_IMG_binary_shader 1
#endif

#ifdef __cplusplus
}
#endif

#endif /* __gl2extimg_h_ */
