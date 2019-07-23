/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 18:49:07 by lterrail          #+#    #+#             */
/*   Updated: 2019/06/27 15:27:58 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_err						g_errs[] =
{
	{-10, "\e[31mOPEN_RT_FILE_FAILED\n\e[39m"},
	{-11, "\e[31mRT_FILE_TOO_BIG\n\e[39m"},
	{-12, "\e[31mFAILED_TO_MALLOC\n\e[39m"},
	{-13, "\e[31mERR_TOO_MANY_SCENE\n\e[39m"},
	{-14, "\e[31mERR_TOO_MANY_CAMERA\n\e[39m"},
	{-15, "\e[31mERR_TOO_MANY_OBJECTS\n\e[39m"},
	{-16, "\e[31mERR_TOO_MANY_LIGHTS\n\e[39m"},
	{-17, "\e[31mERR_TOO_MANY_PARAM\n\e[39m"},
	{-18, "\e[31mERR_NO_SCENE\n\e[39m"},
	{-19, "\e[31mERR_NO_CAMERA\n\e[39m"},
	{-20, "\e[31mERR_NO_OBJECTS\n\e[39m"},
	{-21, "\e[31mERR_NO_LIGHTS\n\e[39m"},
	{-22, "\e[31mERR_NO_LIGTH\n\e[39m"},
	{-23, "\e[31mERR_NO_PARAM\n\e[39m"},
	{-24, "\e[31mERR_NO_ELEM\n\e[39m"},
	{-25, "\e[31mWRONG_EMBRACE\n\e[39m"},
	{-26, "\e[31mERR_CAMERA\n\e[39m"},
	{-27, "\e[31mWRONG_ELEM_NAME\n\e[39m"},
	{-28, "\e[31mWRONG_MATERIAL_NAME\n\e[39m"},
	{-29, "\e[31mERR_OBJ\n\e[39m"},
	{-30, "\e[31mERR_PARAM\n\e[39m"},
	{-31, "\e[31mERR_LIGHT\n\e[39m"},
	{-32, "\e[31mERR_FILL_LIGHT\n\e[39m"},
	{-33, "\e[31mERR_FILL_OBJ\n\e[39m"},
	{-34, "\e[31mERR_FILL_PARAM\n\e[39m"},
	{-35, "\e[31mOPEN_OBJ_FILE_FAILED\n\e[39m"},
	{-36, "\e[31mOBJ_FILE_TOO_BIG\n\e[39m"},
	{-37, "\e[31mERR_MESH\n\e[39m"},
	{-38, "\e[31mBAD_IMG_EXTENSION\n\e[39m"},
	{-39, "\e[31mBAD_IMG_TYPE\n\e[39m"},
	{-40, "\e[31mSEEK_IMG_FAIL\n\e[39m"},
	{-41, "\e[31mFREAD_FAIL\n\e[39m"},
	{-42, "\e[31mFCLOSE_FAIL\n\e[39m"},
	{-43, "\e[31mMLX_ERROR\n\e[39m"},
	{-44, "\e[31mERR_CREATE_THREAD\n\e[39m"}
};
