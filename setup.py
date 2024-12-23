from setuptools import setup, Extension
import pybind11

# Lista de archivos .cpp que conforman el proyecto
source_files = [
    "src/main.cpp",
    "src/ValuationMathTools.cpp",
    "src/FinancialInstrument.cpp",
    "src/EuropeanOption.cpp",
    "src/Portfolio.cpp",
    "src/python_utils.cpp",
    "src/MoneyMarket.cpp",
    "src/MarketModel.cpp",
    "src/IRCurve.cpp",
    "src/FixedIncome.cpp"
]

ext_modules = [
    Extension(
        "ValuationLibrary",                   # Nombre del módulo
        source_files,                   # Lista de archivos fuente en C++
        include_dirs=[pybind11.get_include(), "src"],  # Directorios de inclusión
        language="c++"
    ),
]

setup(
    name="ValuationLibrary",
    version="0.1",
    author="Jose Ortega Moya",
    description="Una librería Python compilada en C++ con múltiples archivos",
    ext_modules=ext_modules,
    zip_safe=False,
)