#pragma once

void DetourInitilization();
void DetourUninitialization();

void dDebug_Log(Object* message, MethodInfo* method);
void dDebug_LogError(Object* message, MethodInfo* method);
void dDebug_LogException(Exception* exception, MethodInfo* method);
void dDebug_LogWarning(Object* message, MethodInfo* method);
