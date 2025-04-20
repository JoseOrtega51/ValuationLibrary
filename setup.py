from setuptools import setup, Extension
try:
    import pybind11
    pybind11_include = pybind11.get_include()
except ImportError:
    pybind11_include = ""


# Lista de archivos .cpp que conforman el proyecto

source_files = [
    "ValuationLibrary/main.cpp",
    "ValuationLibrary/ValuationMathTools.cpp",
    "ValuationLibrary/FinancialInstrument.cpp",
    "ValuationLibrary/Portfolio.cpp",
    "ValuationLibrary/python_utils.cpp",
    "ValuationLibrary/IRCurve.cpp",
]

#source_files = [
#     "ValuationLibrary/main.cpp",
#     "ValuationLibrary/ValuationMathTools.cpp",
#     "ValuationLibrary/FinancialInstrument.cpp",
#     "ValuationLibrary/EuropeanOption.cpp",
#     "ValuationLibrary/Portfolio.cpp",
#     "ValuationLibrary/python_utils.cpp",
#     "ValuationLibrary/MoneyMarket.cpp",
#     "ValuationLibrary/MarketModel.cpp",
#     "ValuationLibrary/IRCurve.cpp",
#     "ValuationLibrary/FixedIncome.cpp"
# ]

ext_modules = [
    Extension(
        "ValuationLibrary",                   # Nombre del módulo
        source_files,                   # Lista de archivos fuente en C++
        include_dirs=[pybind11_include, "ValuationLibrary"],  # Directorios de inclusión
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