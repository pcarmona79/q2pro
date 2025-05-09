/*
Copyright (C) 2018 Andrey Nazarov

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#pragma once

#if USE_SDL
#include <SDL_opengl.h>
#else
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#ifndef QGLAPI
#define QGLAPI extern
#endif

#ifndef GL_VERSION_4_6
#define GL_TEXTURE_MAX_ANISOTROPY 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY 0x84FF
#endif

// GL 1.1
QGLAPI void (APIENTRYP qglBindTexture)(GLenum target, GLuint texture);
QGLAPI void (APIENTRYP qglBlendFunc)(GLenum sfactor, GLenum dfactor);
QGLAPI void (APIENTRYP qglClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
QGLAPI void (APIENTRYP qglClear)(GLbitfield mask);
QGLAPI void (APIENTRYP qglClearStencil)(GLint s);
QGLAPI void (APIENTRYP qglColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
QGLAPI void (APIENTRYP qglCullFace)(GLenum mode);
QGLAPI void (APIENTRYP qglDeleteTextures)(GLsizei n, const GLuint *textures);
QGLAPI void (APIENTRYP qglDepthFunc)(GLenum func);
QGLAPI void (APIENTRYP qglDepthMask)(GLboolean flag);
QGLAPI void (APIENTRYP qglDisable)(GLenum cap);
QGLAPI void (APIENTRYP qglDrawArrays)(GLenum mode, GLint first, GLsizei count);
QGLAPI void (APIENTRYP qglDrawElements)(GLenum mode, GLsizei count, GLenum type, const void *indices);
QGLAPI void (APIENTRYP qglEnable)(GLenum cap);
QGLAPI void (APIENTRYP qglFinish)(void);
QGLAPI void (APIENTRYP qglFrontFace)(GLenum mode);
QGLAPI void (APIENTRYP qglGenTextures)(GLsizei n, GLuint *textures);
QGLAPI GLenum (APIENTRYP qglGetError)(void);
QGLAPI void (APIENTRYP qglGetFloatv)(GLenum pname, GLfloat *data);
QGLAPI void (APIENTRYP qglGetIntegerv)(GLenum pname, GLint *data);
QGLAPI const GLubyte *(APIENTRYP qglGetString)(GLenum name);
QGLAPI GLboolean (APIENTRYP qglIsEnabled)(GLenum cap);
QGLAPI void (APIENTRYP qglLineWidth)(GLfloat width);
QGLAPI void (APIENTRYP qglPixelStorei)(GLenum pname, GLint param);
QGLAPI void (APIENTRYP qglPolygonOffset)(GLfloat factor, GLfloat units);
QGLAPI void (APIENTRYP qglReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
QGLAPI void (APIENTRYP qglScissor)(GLint x, GLint y, GLsizei width, GLsizei height);
QGLAPI void (APIENTRYP qglStencilFunc)(GLenum func, GLint ref, GLuint mask);
QGLAPI void (APIENTRYP qglStencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
QGLAPI void (APIENTRYP qglTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
QGLAPI void (APIENTRYP qglTexParameterf)(GLenum target, GLenum pname, GLfloat param);
QGLAPI void (APIENTRYP qglTexParameteri)(GLenum target, GLenum pname, GLint param);
QGLAPI void (APIENTRYP qglTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
QGLAPI void (APIENTRYP qglViewport)(GLint x, GLint y, GLsizei width, GLsizei height);

// GL 1.1, compat
QGLAPI void (APIENTRYP qglAlphaFunc)(GLenum func, GLclampf ref);
QGLAPI void (APIENTRYP qglColor4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
QGLAPI void (APIENTRYP qglColorPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);
QGLAPI void (APIENTRYP qglDisableClientState)(GLenum cap);
QGLAPI void (APIENTRYP qglEnableClientState)(GLenum cap);
QGLAPI void (APIENTRYP qglLoadIdentity)(void);
QGLAPI void (APIENTRYP qglLoadMatrixf)(const GLfloat *m);
QGLAPI void (APIENTRYP qglMatrixMode)(GLenum mode);
QGLAPI void (APIENTRYP qglScalef)(GLfloat x, GLfloat y, GLfloat z);
QGLAPI void (APIENTRYP qglShadeModel)(GLenum mode);
QGLAPI void (APIENTRYP qglTexCoordPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);
QGLAPI void (APIENTRYP qglTexEnvf)(GLenum target, GLenum pname, GLfloat param);
QGLAPI void (APIENTRYP qglTranslatef)(GLfloat x, GLfloat y, GLfloat z);
QGLAPI void (APIENTRYP qglVertexPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);

// GL 1.1, not ES
QGLAPI void (APIENTRYP qglClearDepth)(GLdouble depth);
QGLAPI void (APIENTRYP qglDepthRange)(GLdouble near, GLdouble far);
QGLAPI void (APIENTRYP qglPolygonMode)(GLenum face, GLenum mode);

// GL 1.3
QGLAPI void (APIENTRYP qglActiveTexture)(GLenum texture);

// GL 1.3, compat
QGLAPI void (APIENTRYP qglClientActiveTexture)(GLenum texture);

// GL 1.5
QGLAPI void (APIENTRYP qglBindBuffer)(GLenum target, GLuint buffer);
QGLAPI void (APIENTRYP qglBufferData)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
QGLAPI void (APIENTRYP qglBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
QGLAPI void (APIENTRYP qglDeleteBuffers)(GLsizei n, const GLuint *buffers);
QGLAPI void (APIENTRYP qglGenBuffers)(GLsizei n, GLuint *buffers);

// GL 1.5, ES 3.0
QGLAPI void (APIENTRYP qglBeginQuery)(GLenum target, GLuint id);
QGLAPI void (APIENTRYP qglDeleteQueries)(GLsizei n, const GLuint *ids);
QGLAPI void (APIENTRYP qglEndQuery)(GLenum target);
QGLAPI void (APIENTRYP qglGenQueries)(GLsizei n, GLuint *ids);
QGLAPI void (APIENTRYP qglGetQueryObjectuiv)(GLuint id, GLenum pname, GLuint *params);

// GL 2.0
QGLAPI void (APIENTRYP qglAttachShader)(GLuint program, GLuint shader);
QGLAPI void (APIENTRYP qglBindAttribLocation)(GLuint program, GLuint index, const GLchar *name);
QGLAPI void (APIENTRYP qglCompileShader)(GLuint shader);
QGLAPI GLuint (APIENTRYP qglCreateProgram)(void);
QGLAPI GLuint (APIENTRYP qglCreateShader)(GLenum type);
QGLAPI void (APIENTRYP qglDeleteProgram)(GLuint program);
QGLAPI void (APIENTRYP qglDeleteShader)(GLuint shader);
QGLAPI void (APIENTRYP qglDrawBuffers)(GLsizei n, const GLenum *bufs);
QGLAPI void (APIENTRYP qglDisableVertexAttribArray)(GLuint index);
QGLAPI void (APIENTRYP qglEnableVertexAttribArray)(GLuint index);
QGLAPI void (APIENTRYP qglGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
QGLAPI void (APIENTRYP qglGetProgramiv)(GLuint program, GLenum pname, GLint *params);
QGLAPI void (APIENTRYP qglGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
QGLAPI void (APIENTRYP qglGetShaderiv)(GLuint shader, GLenum pname, GLint *params);
QGLAPI GLint (APIENTRYP qglGetUniformLocation)(GLuint program, const GLchar *name);
QGLAPI void (APIENTRYP qglLinkProgram)(GLuint program);
QGLAPI void (APIENTRYP qglShaderSource)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
QGLAPI void (APIENTRYP qglUniform1i)(GLint location, GLint v0);
QGLAPI void (APIENTRYP qglUseProgram)(GLuint program);
QGLAPI void (APIENTRYP qglVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
QGLAPI void (APIENTRYP qglVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

// GL 3.0
QGLAPI void (APIENTRYP qglBindBufferBase)(GLenum target, GLuint index, GLuint buffer);
QGLAPI void (APIENTRYP qglBindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
QGLAPI void (APIENTRYP qglBindFramebuffer)(GLenum target, GLuint framebuffer);
QGLAPI void (APIENTRYP qglBindRenderbuffer)(GLenum target, GLuint renderbuffer);
QGLAPI void (APIENTRYP qglBindVertexArray)(GLuint array);
QGLAPI GLenum (APIENTRYP qglCheckFramebufferStatus)(GLenum target);
QGLAPI void (APIENTRYP qglClearBufferfv)(GLenum buffer, GLint drawbuffer, const GLfloat *value);
QGLAPI void (APIENTRYP qglDeleteFramebuffers)(GLsizei n, const GLuint *framebuffers);
QGLAPI void (APIENTRYP qglDeleteRenderbuffers)(GLsizei n, const GLuint *renderbuffers);
QGLAPI void (APIENTRYP qglDeleteVertexArrays)(GLsizei n, const GLuint *arrays);
QGLAPI void (APIENTRYP qglFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
QGLAPI void (APIENTRYP qglFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
QGLAPI void (APIENTRYP qglGenFramebuffers)(GLsizei n, GLuint *framebuffers);
QGLAPI void (APIENTRYP qglGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
QGLAPI void (APIENTRYP qglGenVertexArrays)(GLsizei n, GLuint *arrays);
QGLAPI void (APIENTRYP qglGenerateMipmap)(GLenum target);
QGLAPI void (APIENTRYP qglGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint *params);
QGLAPI const GLubyte *(APIENTRYP qglGetStringi)(GLenum name, GLuint index);
QGLAPI void (APIENTRYP qglRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
QGLAPI void (APIENTRYP qglVertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);

// GL 3.0, not ES
QGLAPI void (APIENTRYP qglBindFragDataLocation)(GLuint program, GLuint colorNumber, const GLchar *name);

// GL 3.1
QGLAPI void (APIENTRYP qglGetActiveUniformBlockiv)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
QGLAPI GLuint (APIENTRYP qglGetUniformBlockIndex)(GLuint program, const GLchar *uniformBlockName);
QGLAPI void (APIENTRYP qglTexBuffer)(GLenum target, GLenum internalformat, GLuint buffer);
QGLAPI void (APIENTRYP qglUniformBlockBinding)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

// GL 3.2
QGLAPI GLenum (APIENTRYP qglClientWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
QGLAPI void (APIENTRYP qglDeleteSync)(GLsync sync);
QGLAPI GLsync (APIENTRYP qglFenceSync)(GLenum condition, GLbitfield flags);

// GL 4.1
QGLAPI void (APIENTRYP qglClearDepthf)(GLfloat d);
QGLAPI void (APIENTRYP qglDepthRangef)(GLfloat n, GLfloat f);

// GL 4.3
QGLAPI void (APIENTRYP qglDebugMessageCallback)(GLDEBUGPROC callback, const void *userParam);
QGLAPI void (APIENTRYP qglDebugMessageControl)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);

// GL 4.4
QGLAPI void (APIENTRYP qglBindTextures)(GLuint first, GLsizei count, const GLuint *textures);

// GL 4.5
QGLAPI void (APIENTRYP qglBindTextureUnit)(GLuint unit, GLuint texture);
QGLAPI void (APIENTRYP qglReadnPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);

// GL_ARB_fragment_program
QGLAPI void (APIENTRYP qglBindProgramARB)(GLenum target, GLuint program);
QGLAPI void (APIENTRYP qglDeleteProgramsARB)(GLsizei n, const GLuint *programs);
QGLAPI void (APIENTRYP qglGenProgramsARB)(GLsizei n, GLuint *programs);
QGLAPI void (APIENTRYP qglProgramLocalParameter4fvARB)(GLenum target, GLuint index, const GLfloat *params);
QGLAPI void (APIENTRYP qglProgramStringARB)(GLenum target, GLenum format, GLsizei len, const void *string);

// GL_EXT_compiled_vertex_array
QGLAPI void (APIENTRYP qglLockArraysEXT)(GLint first, GLsizei count);
QGLAPI void (APIENTRYP qglUnlockArraysEXT)(void);

bool QGL_Init(void);
void QGL_Shutdown(void);
