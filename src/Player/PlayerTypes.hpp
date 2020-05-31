#pragma once
#include <string>
#include <map>
namespace Senseless{
//
//
//
struct TeamData {
    std::string shirt_name;
    int shirt_number = 0;
    };
struct Attributes {};
enum class RunningSpeed { VerySlow, Slow, Normal, Fast, VeryFast };
//
//
//
inline std::map<RunningSpeed, float> run_speeds = {
    {RunningSpeed::VerySlow, 0.75F}, {RunningSpeed::Slow, 1.0F},     {RunningSpeed::Normal, 1.5F},
    {RunningSpeed::Fast, 2.0F},      {RunningSpeed::VeryFast, 2.5F},
    };
//
//
//
inline std::map<RunningSpeed, float> dribble_speeds = {
    {RunningSpeed::VerySlow, 0.25F}, {RunningSpeed::Slow, 0.5F},     {RunningSpeed::Normal, 1.0F},
    {RunningSpeed::Fast, 1.5F},      {RunningSpeed::VeryFast, 2.0F},
    };
//
//
//
inline std::map<RunningSpeed, float> kick_mods = {
    {RunningSpeed::VerySlow, 0.7F}, {RunningSpeed::Slow, 1.1F},     {RunningSpeed::Normal, 1.3F},
    {RunningSpeed::Fast, 2.0F},     {RunningSpeed::VeryFast, 2.9F},
    };
}
